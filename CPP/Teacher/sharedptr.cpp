#include <iostream>
#include <map>

using namespace std;

class A
{
public:
    A():m_data(10) {}
    A(A &&) = default;
    A(const A &) = default;
    A &operator=(A &&) = default;
    A &operator=(const A &) = default;
    ~A() = default;
    void foo() { cout << "A::foo()" << endl;}
    void bar() { cout << m_data << endl;}
private:
    int m_data;
};

class smart_ptr
{
public:
    smart_ptr(A* pa);
    smart_ptr(smart_ptr& spa);
    smart_ptr& operator=(smart_ptr& spa);
    ~smart_ptr();
    A* operator->() const noexcept { return m_pa;}
    A& operator*() const noexcept { return *m_pa;}
    int use_count() const { return m_cnt[m_pa]; }
    A* get() const { return m_pa;}
private:
    A* m_pa;
    static map<A*, uint64_t> m_cnt;
};

map<A*, uint64_t> smart_ptr::m_cnt;

smart_ptr::smart_ptr(A* pa) : m_pa(pa)
{
    m_cnt.emplace(m_pa, 1);
}

smart_ptr::~smart_ptr()
{
    if (m_pa != nullptr && m_cnt[m_pa] == 1)
    {
        delete m_pa;
        m_pa = nullptr;
        m_cnt.erase(m_pa);
    }
}

smart_ptr::smart_ptr(smart_ptr& spa): m_pa(spa.m_pa)
{
    m_cnt[m_pa] += 1;
}

smart_ptr& smart_ptr::operator=(smart_ptr& spa)
{
    if (m_pa == spa.m_pa)
    {
        return *this;
    }
    if (m_pa != nullptr && m_cnt[m_pa])
    {
        delete m_pa;
        m_pa = nullptr;
        m_cnt.erase(m_pa);
    }
    m_pa = spa.m_pa;
    m_cnt[m_pa] += 1;
    return *this;
}

int main(int argc, const char** argv) {

    smart_ptr spa(new A());
    smart_ptr spb(spa);
    cout << spa.use_count() << endl;
    spa->foo();
    spa->bar();
    return 0;
}