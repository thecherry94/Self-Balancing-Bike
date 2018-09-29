 #ifndef SINGLETON_H
 #define SINGLETON_H
 
 
 template <typename C>
 class cSingleton
 {
 public:
    static C* instance ()
    {
       if (!_instance)
          _instance = new C ();
       return _instance;
    }
    virtual ~cSingleton ()
    {
       _instance = 0;
    }
 private:
    static C* _instance;
 protected:
    cSingleton () { }
 };
 template <typename C> C* cSingleton <C>::_instance = 0;

/* Verwendung */
/*
 class Test : public cSingleton <Test>
 {
 friend class cSingleton <Test>;
 public:
    ~Test () { }
    void xyz () { }
 protected:
    Test () { }
 };
 */

#endif