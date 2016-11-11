using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{   
    class Program
    {
        public static void PrintInfo<T>(T [] h)
        {
            foreach(T f in h)
            {
                Console.WriteLine(f);
            }
        } 
        static void Main(string[] args)
        {
            Hero mort = Hero.createHero("Mortred");
            Hero abbadon = Hero.createHero("Abbadon");
            try
            {
                Console.WriteLine(mort.ToString() + "\n" + mort.watchWord);
            }
            catch (Exception err) { Console.Write(err.ToString()); }

            DotaObject tmp = new DotaObject();
            Console.WriteLine(tmp.watchWord);

            DotaMap map = new DotaMap();
            map.heroesStore.HeroList[0].Killing(map.heroesStore.HeroList[1]);
            map.heroesStore.HeroList[0].Killing(abbadon);
            Hero[] hr = new Hero[2];
            hr[0] = mort;
            hr[1] = abbadon;
            PrintInfo(hr);
            Console.Read();          
        }
    }

    public class HeroDamageArgs
    {
        public int damage;
        public HeroDamageArgs(int damage)
        {
            this.damage = damage;
        }
    }
    public class NotAnoughHeroDamageExeption : Exception
    {
        public NotAnoughHeroDamageExeption(){
                   
        }
        public NotAnoughHeroDamageExeption(string msg) : base(msg) { }

        static public bool checkArgs(HeroDamageArgs args)
        {
            if (args.damage < 100)
                return true;
            return false;
        }
    }

    public abstract class HeroAbstract
    {
        abstract public void Killing(Hero hero);
    }
    public abstract class Meth{
        public abstract double DamagePerSecond();
    }
    
    interface Prop1
    {
        string name { get; }
        string objType { get; }
        int health { get; }
        double healthRegeneration { get; }
        string watchWord { get; }

    }
    interface Prop2
    {
        int mana { get; }
    }
    public class DotaObject : Meth, Prop1
    {
        public static bool dotaobj;
        public static int MinHealth;
        protected string type;
        private string Name;
        protected int Health;
        protected double HealthRegeneration;

        static DotaObject()
        {
            MinHealth = 1;
            dotaobj = true;
        }
        public DotaObject()
        {
            this.type = "DotaObject";
            this.Name = "Default name";
            this.Health = 0;
            this.HealthRegeneration = 0.0;
        }
        public DotaObject(string name, int health, double regeneration)
        {
            this.type = "DotaObject";
            this.Name = name;
            this.Health = health;
            this.HealthRegeneration = regeneration;
        }

        public string name
        {
            get { return Name; }
        }
        public string objType
        {
            get { return type; }
        }
        public int health
        {
            get { return Health; }
            set
            {
                if (value < 1)
                {
                    Health = MinHealth;
                }
                else if (value > 10000)
                {
                    value = 99999;
                }
                else Health = value;
            }
        }
        public double healthRegeneration
        {
            get { return HealthRegeneration; }
        }
        public override string ToString()
        {
            return "Type: " + this.type + "   Name: " + this.Name + "/n";
        }
        public virtual string watchWord { get { return "No watchWord"; } }
        public override double DamagePerSecond() { return 0; }
    }

    public class Unit : DotaObject, Prop2
    {
        protected int Mana;
        protected int Attack;
        protected double AttackSpeed;
        protected int Speed;
        protected double ManaRegeneration;
        protected int Armor;
        protected int MagicResistance;

        public Unit(string name, int health, int mana, double regeneration,
            int attack, int attackSpeed, int speed, 
            double manaRegeneration, int armor, int magicResistance) : base (name, health,regeneration)
        {
            this.Mana = mana;
            this.Attack = attack;
            this.AttackSpeed = attackSpeed;
            this.Speed = speed;
            this.ManaRegeneration = manaRegeneration;
            this.Armor = armor;
            this.MagicResistance = magicResistance;
            this.type = "Unit";
        }

        public int mana
        {
            get { return Mana; }
        }
        public override string ToString()
        {
            return base.ToString();
        }
        public override double DamagePerSecond()
        {
            return (double) Attack / AttackSpeed;
        }
    }

    public delegate void HeroKillingHandle(Hero heroAttack, Hero Killed);
     
    public class Hero : Unit
    {
        protected int Strength;
        protected int Agility;
        protected int Intelligence;
        protected string WatchWord;
        public event HeroKillingHandle HeroKillingEvent;
        private Hero(int strength, int agility, int intelligence, string watchword,
            string name, int health, int mana, double regeneration,
            int attack, int attackSpeed, int speed,
            double manaRegeneration, int armor, int magicResistance) : 
            base(name, health, mana, regeneration, attack, attackSpeed, speed, manaRegeneration,
            armor, magicResistance)
        {
            this.Strength = strength;
            this.Agility = agility;
            this.Intelligence = intelligence;
            this.type = "Hero";
            this.WatchWord = watchword;        
        }

        public static Hero createHero(string name)
        {
            if (name == "Mortred")
            {
                return new Hero(20,23,15, "Я размою черту между жизнью и смертью",
                    name,20*25,15*20,0.85,23*2,23*5,315,0.61,4,25);
            }
            else if(name == "Abbadon")
            {
                return new Hero(25, 18, 18, "Я повелитель тьмы!", name, 25 * 25,
                    18 * 20, 1.3, 25 * 2, 18 * 5, 305, 0.78, 3, 25);
            }
            else if(name == "Anti-mage")
            {
                return new Hero(65, 78, 46, "Магия сокрушит тебя", name, 65 * 25,
                    46 * 20, 10, 78 * 2, 46 * 5, 360, 2.4, 11, 60);
            }
            else return null;
        }

        public void KillingMessage(Hero heroAttack, Hero heroKilled)
        {
            Console.WriteLine(heroAttack.name + " was killed by " + heroKilled.name);
        }
        public void Killing(Hero hero)
        {
            try
            {
                HeroDamageArgs args = new HeroDamageArgs(hero.Attack);
                if(NotAnoughHeroDamageExeption.checkArgs(args))
                    throw new NotAnoughHeroDamageExeption("Not enough damage");
                
            }
            catch (NotAnoughHeroDamageExeption exp)
            {
                Console.WriteLine(hero.name + " have " + exp.Message + " to kill " + this.name);
            }
            if (hero.HeroKillingEvent != null)
            {
                HeroKillingEvent(hero, this);
            }
            

        }
        public override string ToString()
        {
            return "Name: " + this.name + "\nType: " + type + "\nAttack: " + Attack + "\nHealth: " +
                Health + "\nMana: " + Mana + "\n";
        }

        public override string watchWord
        {
            get { return WatchWord; }
        }
        
    }

    public class HeroStorage<T> where T : Hero
    {
        public List<T> HeroList;
        public HeroStorage()
        {
            HeroList = new List<T>(100);
        }
        public bool EmptyStorage<T>(T t) where T : Hero
        {
            if(HeroList.Count == 0)
            {
                return true;
            }
            return false;
        }
        
    }
    public class DotaMap
    {
        public HeroStorage<Hero> heroesStore;

        public DotaMap()
        {
            heroesStore = new HeroStorage<Hero>();
            Hero[] heroes = new Hero[2];
            heroes[0] = Hero.createHero("Mortred");
            heroes[1] = Hero.createHero("Anti-mage");
            foreach(Hero h in heroes){
                heroesStore.HeroList.Add(h);
                    
            }
            heroesStore.HeroList[0].HeroKillingEvent += new HeroKillingHandle(heroesStore.HeroList[1].KillingMessage);
            heroesStore.HeroList[1].HeroKillingEvent += new HeroKillingHandle(heroesStore.HeroList[0].KillingMessage);
           
        }
    }

    public class Building : DotaObject
    {

    }

    public class Barracks : Building
    {

    }
    
    public class Tower : Building
    {
        protected int Attack;
        protected int Armor;

    }

}
