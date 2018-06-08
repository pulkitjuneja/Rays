# pathToGimp=/mnt/d/Program\ Files\ \(x86\)/GIMP\ 2/GIMP\ 2/bin/gimp-2.8.exe
g++ -std=c++11 ./RayTracer/main.cpp -o raytracer.out
./raytracer.out

$ptt './finalImage.ppm'
rm ./raytracer.out