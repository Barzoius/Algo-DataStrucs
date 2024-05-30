bool in_triangle(std::pair<int, int> A,  //     B       */
                 std::pair<int, int> B,  //     /\      */
                 std::pair<int, int> C,  //    /  \     */
                 std::pair<int, int> P)  // A /____\ C  */
{
    int w1 , w2;

    w1 = ( (A.first * (C.second - A.second)) +
         ( (P.second - A.second) * (C.first - A.first)) -
         (  P.first * (C.second - A.second))  )
                 /
         (B.second - A.second) * (C.first - A.first) -
         (B.first - A.first) *(C.second - A.second);
    std::cout<<w1<<"\n";
    w2 = (P.second - A.second - w1 * (B.second - A.second))
            /
         (C.second - A.second);
    std::cout<<w1<<"\n";

    if((w1 >= 0) && (w2 >= 0) && ((w1 + w2) <= 1)) {
        std::cout << "INSIDE";
        return true;
    }
    else {
        std::cout<<"OUTSIDE";
        return false;
    }

}
