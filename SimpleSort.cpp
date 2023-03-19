void SimpleSort(std::vector<int>& v)
{
    for (int i = 1; i < v.size(); i++)
   {
        for (int j = 1; j < v.size(); j++)
        {
            if (v[i] < v[j])
            {
               std::swap(v[i], v[j]);
            }
        }
    }
}
