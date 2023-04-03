void SimpleSort(std::vector<int>& v)
{
    for (int i = 0; i < v.size(); i++)
   {
        for (int j = 0; j < v.size(); j++)
        {
            if (v[i] < v[j])
            {
               std::swap(v[i], v[j]);
            }
        }
    }
}
