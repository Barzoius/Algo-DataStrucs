#include <iostream>

template <typename T>
class VECTOR{

private:
    T* vector;
    int size;
    int Size;

public:
    VECTOR()
    {
        vector = new T[1];
        size = 0;
        Size = 1;

    }

    ~VECTOR()
    {
        delete [] vector;
    }

    void Push_Back(T element)
    {
        if(size == Size)
        {
            T* aux = new T[size + 1];

            for(int i = 0; i < Size; i++)
            {
                aux[i] = vector[i];
            }

            delete[] vector;
            Size = size +1 ;
            vector = aux;
        }

        vector[size] = element;
        size++;
    }

    ///---Insertion over element---///
    void Insert(T element, int index)
    {
        if(index == size)
            Push_Back(element);
        else
            vector[index] = element;
    }

    T POP()
    {
        T LAST = vector[size - 1];
        size--;
        return LAST;

    }

    int SIZE() { return size; }

    int DIMENISION() { return Size; }

    const T& operator [](size_t index) const
    {
        if(index >= size)
        {
            throw std::out_of_range("INDEX OUT OF RANGE!");
        }
        return vector[index];

    }
    
    void REZERVE(int new_size)
    {
        if(new_size <= Size)
        {
            return;
        }

        T* aux = new T[new_size];
        for(int i = 0; i < Size; i++)
        {
            aux[i] = vector[i];
        }

        delete[] vector;

        vector = aux;
        Size = new_size;
    }

};

int main() {

    VECTOR<int> v;
    v.Push_Back(12);
    v.Push_Back(78);
    v.Push_Back(12);
    v.Push_Back(42);
    v.Push_Back(13);
    std::cout<<v.POP();
    std::cout<<std::endl;

    std::cout<<v.SIZE();
    std::cout<<std::endl;
    std::cout<<v.DIMENISION();
    std::cout<<std::endl;
    std::cout<<v.POP();
    //std::cout<<v[4];
    return 0;
}
