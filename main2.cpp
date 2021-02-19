//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x86

#include <iostream>
#include <cstdlib>

/** Root class that will contain all worlds in the game. Designed as singleton
* see https://de.wikibooks.org/wiki/C%2B%2B-Programmierung:_Entwurfsmuster:_Singleton
* 
* Every single software object of any possible class in the virtual world(s) contained 
* or referred in this program will get an uinque ID and will keep it for the rest of
* its life. The ID-s are not intended to be reused; after destroying an object, its ID
* is lost. Any new object will get the next available ID provided by the root singleton.
*/
class CRoot
 {
    int m_id; // added: get an unique Id
 public:
    static CRoot* instance ()
    {
       static CGuard g;   // Speicherbereinigung
       if (!_instance)
          _instance = new CRoot ();
       return _instance;
    }
    void xyz () {std::cout<<"instance: id: "<<m_id<<std::endl;} /** added; a testing function */
    int getNextId(){return ++m_id;} // added; attributes a new Id
    int getCrtId(){return m_id;} // added: returns an id
    void releaseId(int id){} // NOTE: I have no idea what to do with it...
 private:
    static CRoot* _instance;
    CRoot (): m_id(0) { } /* verhindert, dass ein Objekt von außerhalb von N erzeugt wird. */
              // protected, wenn man von der Klasse noch erben möchte
    CRoot ( const CRoot& ); /* verhindert, dass eine weitere Instanz via
 Kopie-Konstruktor erstellt werden kann */
    ~CRoot () { }
    class CGuard
    {
    public:
       ~CGuard()
       {
          if( 0 != CRoot::_instance )
          {
             delete CRoot::_instance;
             CRoot::_instance = 0;
          }
       }
    };
 };

CRoot* CRoot::_instance = 0; /* statische Elemente einer Klasse müssen initialisiert werden. */

/** CEntity declared befor the CNode because a node can contain one (or more) entities */
class CEntity;

/** A scene node that can contain another nodes
*  A scene node is intended to be anything that can have a physical representation in the virtual world
* that supports a single transformation.
* Like an entity, a light source, a camera or an empty thing serving as transformation base 
* for the subsequent nodes
*/
class CNode
{
protected:
    CNode** m_children;
    int m_childCount;
    CEntity** m_entities;
    int m_entityCount;
public:
    CNode(): m_children(0), m_childCount(0){}
    ~CNode(){if(m_children) delete m_children;}
    CNode** getChildren(){return m_children;}
    void addChildren(CNode** children, int nHowMany)
    {
        if(!children) // the very first child or set of children to be added
        {
            m_children = children;
            m_childCount = nHowMany;
        }
        else // there are already children attached
        {
            void* newChildren = (CNode**)realloc(m_children, nHowMany*sizeof(CNode*));
            if(newChildren)
            {
                m_children = (CNode**)newChildren;
                m_childCount+=nHowMany;
            }
            else
            {
                std::cout<<"cannot add "<<nHowMany<<" child nodes at address: "<<newChildren<<std::endl;
            }
        }
    }
};

/** Like in real life, a scene is a well defined part of the world resembling the reality where 
* entities are put in and a series of actions take place */
class CScene
{
protected:
    CNode** m_nodes;
    int m_nodeCount;
public:
    CScene(): m_nodes(0), m_nodeCount(0){} // starting as an empty scene
    
};

class CEntity 
{
protected:
    CRoot* m_root;
    int m_id;
public:
    CEntity():m_root(CRoot::instance()), m_id(m_root->getNextId()){}
    int getId(){return m_id;}
    virtual ~CEntity(){}
    // int getID(){}
};

/** a class  */
class CWorld
{
    CEntity** m_entities;
    unsigned m_entityCount;
public:
    CWorld(){}
    virtual ~CWorld(){if(m_entities) delete m_entities;}
    virtual void addEntity(CEntity* entity)
    {
        if(m_entities)
        {
            
        }
        else
        {
            m_entities = new CEntity*[1];
        }
    }
};

/** an organic entity: base for life forms */
class COrganic: public virtual CEntity
{
public:
};

/** an anorganic entity, not base for life forms but for any other object */
class CAnorganic: public virtual CEntity
{
public:
};

/** a concrete anorganic object (not final) than can hold another entities */
class CBuilding: public virtual CAnorganic
{
public:
    
};

/** Biotope is a world containing organic an anorganic entities */
class CBiotope
{
public:
    
};

/** An ecosystem is a system containing only biotopes */
class CEcocystem
{
public:
};
    
/**  generic class for life form to be implemented by plants and animals */
class CLifeForm: public COrganic
{
protected:
    bool m_isAlive; // 
    float m_health; // 0. to 1.
    float m_weight; // 0. to max
    float m_growRate; // species specific; for plants another meaning as for animals
    float m_maxWeight; // a constant for a designated species
    const char* m_szName; // a life form can have a name or not
    float m_energy; // the enery it haves, depends on a quotient multiplied with its mass
public:
    CLifeForm():m_isAlive(true), m_health(1.f), m_weight(1.f){}
    virtual ~CLifeForm(){m_isAlive = false;}
    virtual float getHealth(){return m_health;}
    virtual bool alive(){return m_isAlive;}
};

// generic class for vegetal life forms
class CPlant: public virtual CLifeForm 
{
protected:
    
public:
    CPlant(): CLifeForm(){}
    // a plant is growing till to its max weight as time goes by
    virtual void grow(float dt){m_weight+=dt*m_growRate*(m_weight<m_maxWeight); m_health+=dt*m_growRate/m_maxWeight*(m_health<0.999f);}

};

// final class for a designated species of plant 
class CGrass final: public CPlant 
{
protected:
public:
    CGrass(): CPlant(){m_growRate = 0.02f;}
};

// generic class for animal life forms
class CAnimal: public virtual CLifeForm 
{
protected:
    float m_energyRes;
public:
    CAnimal():CLifeForm(), m_energyRes(0.f){}
    virtual void eating(){std::cout<<"generic food\n";}
    virtual void eat(CLifeForm* other) = 0{}
    virtual bool canEat(CLifeForm* other) = 0{}
    /** An animal is growing till to its max weight as time goes by only is eating regulary.
    * Its energy decreases as time goes by but get a new amount after eating something */
    virtual void grow(float dt){m_energy-= m_weight+=dt*m_growRate*m_energy*(m_weight<m_maxWeight); m_health+=dt*m_growRate/m_maxWeight*(m_health<0.999f);}
    
};

// generic class for carnivore animals
class CCarnivore: public virtual CAnimal 
{
public:
    virtual void eating(){std::cout<<"animal food\n";}
    
    virtual bool canEat(CLifeForm* other) = 0{}
    virtual void eat(CLifeForm* other) = 0{}
};

// generic class for herbivore animals
class CHerbivore: public virtual CAnimal 
{
public:
    virtual void eating(){std::cout<<"vegetal food\n";}
    
    virtual bool canEat(CLifeForm* other){return dynamic_cast<CPlant*>(other);}
    virtual void eat(CLifeForm* other) = 0{}
};

// generic clas for omnivores
/** they have both herbivore and carnivore features */
class COmnivore: public CCarnivore, public CHerbivore 
{
public:
    virtual bool canEat(CLifeForm* other){return true;}
    virtual void eat(CLifeForm* other){}
    virtual void eating(){std::cout<<"any kind of food\n";}
};

// Generic class for pets
/** a special kind of animals that will get obligatory a name 
 they can be herbivore and carnivore as well */
class CPet: public virtual CAnimal 
{
protected:
    const char* m_szName;
public:
    CPet() = delete;
    CPet(const char* szName):m_szName(szName){}
    
};

// an example of a pet carnivore animal (final)
class CDog final: public CCarnivore, public CPet
{
public:
    CDog(const char* szName): CPet(szName){}
    
};

// another example of a pet herbivore animal (final)
class CHamster final: public CHerbivore, public CPet
{
public:
    CHamster(const char* szName): CPet(szName){}
};

//////////////////////////////////////////////////////////////////////////

void testSingleton()
{
    CRoot* root = CRoot::instance();
    std::cout<<root->getCrtId()<<std::endl;
    std::cout<<root->getNextId()<<std::endl;
    std::cout<<root->getNextId()<<std::endl;
    std::cout<<root->getNextId()<<std::endl;
    
    CRoot* root2 = CRoot::instance();
    std::cout<<root->getNextId()<<std::endl;
    std::cout<<root->getNextId()<<std::endl;
    std::cout<<root->getNextId()<<std::endl;
    
}

int main()
{
    testSingleton();
    std::cout << "Hello, world!\n";
}


