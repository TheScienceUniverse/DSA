rm -rf DSA
git clone https://github.com/TheScienceUniverse/DSA.git
cd DSA

mkdir -p ./obj/ ./lib/ ./bin/

make clean
make all

mkdir -p ../lib/
cp ./lib/libdsa.so ../lib/

cd ../
# rm -rf ./DSA/
