#pragma once

#ifndef interface
#define interface struct
#endif

interface NavigateWnd;

#include <vector>
#include <string>

namespace comp
{
    enum CompAttr{leaf, component};
    enum CompType{unknown, condition, command, all};

    interface Composite
    {
        virtual ~Composite(){};
        // Component -----------------------------------------------------------
        // Query
        virtual bool CanAddChild(const Composite * pChild) const = 0;
        virtual bool HaveRoom() const = 0;
		virtual bool CheckValid() const = 0;
        // Modify
        virtual bool AddChild(Composite *pChild) = 0;
        virtual bool DelChild(Composite *pChild) = 0;
        virtual bool ChgChild(Composite *pOldChild, Composite *pNewChild) = 0;
        virtual bool ClearAll() = 0;
        // Visit
        virtual void BeginEnumChild() = 0;
        virtual Composite * GetNextChild() = 0;

        // Prototype -----------------------------------------------------------
        virtual Composite * Clone() const = 0;

        // Read/Save -----------------------------------------------------------
        virtual bool Read(std::istream & is) = 0;
        virtual bool Save(std::ostream & os, int indent = 0) const = 0;

        // Configure self-------------------------------------------------------
        virtual bool Configure(const std::string& str) = 0;
        virtual std::string GetConfiguration() const = 0;

        // Information ---------------------------------------------------------
        virtual std::string GetName() const = 0;
        virtual std::string GetDescription() const = 0;
    };

    typedef std::vector<Composite *> CompositeArray;

    class Component : public Composite
    {
    public:
        Component();
        virtual ~Component();

        virtual bool HaveRoom() const;
		virtual bool CheckValid() const;
        virtual bool AddChild(Composite *pChild);
        virtual bool DelChild(Composite *pChild);
        virtual bool ChgChild(Composite *pOldChild, Composite *pNewChild);
        virtual bool ClearAll();
        virtual void BeginEnumChild();
        virtual Composite * GetNextChild();
        virtual Composite * Clone() const;
        virtual bool Read(std::istream & is);
        virtual bool Save(std::ostream & os, int indent = 0) const;
        virtual bool Configure(const std::string& str);
        virtual std::string GetConfiguration() const;
    private:
        // trivial copy, subclass XXX should simply implement this function like
        // this: return new XXX;
        virtual Component * CreateObject() const = 0;

        // iterator for visiting
        CompositeArray::iterator m_currIter;

    protected:
        // array of children
        CompositeArray m_arrComp;
    };

    class Leaf : public Composite
    {
    public:
        Leaf();
        virtual ~Leaf();
        virtual bool CanAddChild(const Composite * pChild) const ;
        virtual bool HaveRoom() const;
        virtual bool AddChild(Composite *pChild);
        virtual bool DelChild(Composite *pChild);
        virtual bool ChgChild(Composite *pOldChild, Composite *pNewChild);
        virtual bool ClearAll();
        virtual void BeginEnumChild();
        virtual Composite * GetNextChild();
        virtual Composite * Clone() const;
        virtual bool Read(std::istream & is);
        virtual bool Save(std::ostream & os, int indent = 0) const;
    private:
        // trivial copy, subclass XXX should simply implement this function like
        // this: return new XXX;
        virtual Leaf * CreateObject() const = 0;
    };


}