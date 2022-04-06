template<class T>
int find_last_of(const vector<T>& v, const T& x)
{ 
    int occurance = 0;
    for(int i=0; i < v.size(); i++)
    {
        if (v[i] == x)
        {
            occurance = i;
        }  
    }
    if (occurance != 0)
    {
        return occurance;
    }
    else
    {
        return -1;
    }
}