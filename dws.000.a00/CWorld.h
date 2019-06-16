
#include "CAssets.h"

class CWorld;

class CWorld
{
    CWorld()
    {
        std::cout<<"new world created .........................."<<std::endl;
    }                    // Constructor? (the {} brackets) are needed here.
    ~CWorld()
    {
        std::cout<<"......................... world destroyed"<<std::endl;

    } // destructor for ...
    
    
public:
    static CWorld* m_pinstance;
    static CWorld& getInstance()
    {
        static CWorld    instance; // Guaranteed to be destroyed.
                              // Instantiated on first use.
        return instance;
    }
    static CWorld* getInstance(void*)
    {
        if(nullptr==m_pinstance)
            m_pinstance = new CWorld();
        return m_pinstance;
    }
    static CWorld* release()
    {
        if(m_pinstance) delete m_pinstance;
        m_pinstance = nullptr;
    }

    // C++ 03
    // ========
    // Don't forget to declare these two. You want to make sure they
    // are unacceptable otherwise you may accidentally get copies of
    // your singleton appearing.\
    
    // CWorld(CWorld const&);              // Don't Implement
    // void operator=(CWorld const&); // Don't implement
       /*******/ 
    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.

public:
    CWorld(CWorld const&)          = delete;
    void operator=(CWorld const&)  = delete;

    // Note: Scott Meyers mentions in his Effective Modern
    //       C++ book, that deleted functions should generally
    //       be public as it results in better error messages
    //       due to the compilers behavior to check accessibility
    //       before deleted status
    
    // Create assets:
    CAsset* clone(CAsset* original)
    {
        return new CAsset(*original);
    }
    
    CAsset* spawn(int clsId = 0)
    {
        switch(clsId)
        {
        case ID_GENERIC:
            return new CAsset();
            break;
        case ID_LIFEFORM:
            // return new CLifeForm();
            std::cout<<"which class of life form?\n";
            break;
        case ID_PLANT:
            // return new CPlant();
            std::cout<<"which kind of plant?\n";
            break;
        case ID_ANIMAL:
            std::cout<<"which kind of animal?\n";
            // return new CAnimal();
            break;
        case ID_ANIMAL_HERBIVORE:
            // return new CHerbivore();
            std::cout<<"which kind of herbivore?\n";
            break;
        }
        return nullptr;
    }
    
    void release(CAsset* asset)
    {
        if(asset) delete asset;
        asset = nullptr;
    }
};

CWorld* CWorld::m_pinstance = nullptr;


