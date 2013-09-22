#ifndef SINGLETON_H
#define SINGLETON_H


template <class T>
class Singleton {
private:
	static T m_instance;
public:
	static T *instance(void) { return &m_instance; }
};

template <class T>
T Singleton<T> :: m_instance; 



//template <class T>
//class Singleton {
//private:
//	static T * m_pTInstance;
//public:
//	static T * instance(void);
//    static void clean();
//};
//
//template <class T>
//T * Singleton<T> :: instance(void) {
//	if(m_pTInstance == 0) {
//		m_pTInstance = new T();
//	}
//	return(m_pTInstance); 
//}
//
//template <class T>
//void Singleton<T> :: clean() {
//	delete(m_pTInstance);
//	m_pTInstance = NULL;
//}
//
//template <class T>
//T * Singleton<T> :: m_pTInstance = 0; 

#endif /* SINGLETON_H */
