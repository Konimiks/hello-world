#include "workers.h"

int workers_fill_array(worker * workers_arr, size_t size)
{
    LIBXML_TEST_VERSION
    xmlDocPtr doc;
    xmlNodePtr cur;
    doc = xmlParseFile("workers.xml");

    if (doc == NULL ) {
        fprintf(stderr,"Document not parsed successfully. \n");
        return;
    }
    cur = xmlDocGetRootElement(doc);
    if (cur == NULL) {
        fprintf(stderr,"empty document\n");
        xmlFreeDoc(doc);
        return;
    }
    xmlNodePtr w = cur->children->next;
    for(int i = 0; i < size && w != NULL; w = w->next, i++)
    {
        if(w->type != XML_ELEMENT_NODE)
        {
            i--;
            continue;
        }
        parse_worker(&workers_arr[i], w);
    }
    xmlFreeDoc(doc);
}

void copy_xmlcontents_to_buffer(char * buffer, xmlNodePtr node)
{
    char * content = xmlNodeGetContent(node);
    strcpy(buffer, content);
}

void parse_worker(worker * w, xmlNodePtr w_node)
{
    xmlNodePtr w_child = w_node->children->next;
    do
    {
        if(w_child->type != XML_ELEMENT_NODE)
            continue;
        if(xmlStrEqual(w_child->name, "name"))
        {
            copy_xmlcontents_to_buffer(w->name, w_child);
        }
        else if(xmlStrEqual(w_child->name, "surname"))
        {
            copy_xmlcontents_to_buffer(w->surname, w_child);
        }
        else if(xmlStrEqual(w_child->name, "company"))
        {
            copy_xmlcontents_to_buffer(w->com.post, w_child);
            copy_xmlcontents_to_buffer(w->com.name, w_child);
            char * post = xmlGetProp(w_child, "post");
            strcpy(w->com.post, post);
            free(post);
        }
        else if(xmlStrEqual(w_child->name, "workingyears"))
        {
            char buffer[MAX_LENGTH];
            copy_xmlcontents_to_buffer(buffer, w_child);
            int years = atoi(buffer);
            w->workingyears = years;
        }
        else if(xmlStrEqual(w_child->name, "birthdate"))
                {
                    struct tm time;
                    memset(&time, 0, sizeof(struct tm));
                    char buffer[MAX_LENGTH];
                    copy_xmlcontents_to_buffer(buffer, w_child);
                    sscanf(buffer, "%i-%i-%i", &(time.tm_year), &(time.tm_mon), &(time.tm_mday));
                    time.tm_year -= 1900;
                    time.tm_mon -= 1;
                    w->birthdate = mktime(&time);
                }

        else if(xmlStrEqual(w_child->name, "salary"))
        {
            xmlNodePtr w_child_sal = w_child->children->next;
            do
            {
                if(w_child_sal->type != XML_ELEMENT_NODE)
                    continue;
                if(xmlStrEqual(w_child_sal->name, "amount"))
                {
                    char buffer[MAX_LENGTH];
                    copy_xmlcontents_to_buffer(buffer, w_child_sal);
                    float amount = atof(buffer);
                    w->sal.amount = amount;
                }
                else if(xmlStrEqual(w_child_sal->name, "valuta"))
                {
                    char buffer[MAX_LENGTH];
                    copy_xmlcontents_to_buffer(w->sal.valuta, w_child_sal);
                }
            }while((w_child_sal = w_child_sal->next) != NULL);
        }
    }while((w_child = w_child->next)!=NULL);
}
