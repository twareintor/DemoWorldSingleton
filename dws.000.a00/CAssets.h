
#include <iostream>


enum
{
    ID_GENERIC,
        ID_OBJECT,
            ID_OBJECT_GENERIC,
            ID_OBJECT_RIGID,
            ID_OBJECT_DEFORMABLE,

        ID_LIFEFORM,
            ID_PLANT,
                ID_PLANT_GENERIC,
                ID_PLANT_INFERIOR,
                ID_PLANT_SUPERIOR,

            ID_ANIMAL,
                ID_ANIMAL_GENERIC,
                ID_ANIMAL_HERBIVORE,
                ID_ANIMAL_CARNIVORE,
                ID_ANIMAL_OMNIVORE,
};


class CAsset
{
    mutable float m_age;
public:
    CAsset():m_age(0.f) {std::cout<<"\nspawned ...";}
    virtual ~CAsset(){std::cout<<"\ndropped ...";}
    virtual void onTick(float dt) const final
    {
        m_age+=dt;
    }
    
};

class CLifeForm: public CAsset
{
protected:
    bool m_sex;
public:
    CLifeForm() = delete;
    void mate(const CLifeForm& other)
    {
        
    }
    CLifeForm& replicate()
    {
        
    }
    CLifeForm* replicate(void*)
    {
		
    }
    
};

class CPlant: public virtual CLifeForm
{
public:
    CPlant() = delete;
    virtual ~CPlant(){}
    
};

class CAnimal: public virtual CLifeForm
{
public:
    virtual bool canEat(CLifeForm* other) = 0;
};

class CHerbivore: public CAnimal
{
public:
    CHerbivore() = delete;
    virtual ~CHerbivore(){}
    virtual bool canEat(CLifeForm* other)
    {
        return dynamic_cast<CPlant*>(other);
    }
};

class CCarnivore: public CAnimal
{
public:
    CCarnivore() = delete;
    virtual bool canEat(CLifeForm* other)
    {
        return dynamic_cast<CHerbivore*>(other);
    }
};

