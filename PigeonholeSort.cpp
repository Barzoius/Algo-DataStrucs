void pigeonholeSort(std::vector<int>& v) {
    int minVal = v[0];
    int maxVal = v[0];

    //Cautam valuarea maxima si minima
    for (int i = 1; i < v.size(); i++) {
        if (v[i] < minVal) {
            minVal = v[i];
        }
        if (v[i] > maxVal) {
            maxVal = v[i];
        }
    }

    int range = maxVal - minVal + 1;

    // se creeaza un vector de "gauri de porumbel"(tot vectori)
    std::vector<int> holes(range, 0);

    // Se pune fiecare element in "gaura de prumbel" corespunzatoare
    for (int i = 0; i < v.size(); i++) 
    {
        holes[v[i] - minVal]++;
    }

    // Punem elementele inapoi in vectorul initial
    int index = 0;
    for (int i = 0; i < range; i++)
    {
        while (holes[i] > 0) 
        {
            v[index] = i + minVal;
            index++;
            holes[i]--;
        }
    }
}
