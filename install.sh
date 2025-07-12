rm -rf DSA
git clone https://github.com/TheScienceUniverse/DSA.git
cd DSA

mkdir -p ./inc/ ./obj/ ./lib/ ./bin/

make clean
make all

mkdir -p ../inc/ ../lib/ ../log/
cp ./inc/* ../inc/
cp ./lib/libdsa.so ../lib/

cd ../
rm -rf ./DSA/
