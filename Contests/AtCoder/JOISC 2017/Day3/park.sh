g++ grader.cpp NaturalPark.cpp -o park -O2 -std=c++11

while true; do
    python3 ./gen.py || break
    ./park < ./park.in || break
done
