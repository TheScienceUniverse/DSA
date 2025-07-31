echo "Cleaning residue..."
rm -rf ./DSA/

echo "Fetching latest version..."
git clone https://github.com/TheScienceUniverse/DSA.git

cd ./DSA/

echo "Setting up directories..."
mkdir -p ./obj/ ./lib/ ./bin/

echo "Building library..."
make clean
make all

echo "Creating log directory (DON'T DELETE)..."
mkdir -p ../log/
#cp ./inc/* ../inc/
#cp ./lib/libdsa.so ../lib/

echo "Cleaning up...";
rm -rf ./.git/ ./.github/ ./aft/ ./bin/ ./cov/ ./doc/ ./font/ ./log/ ./media/ ./obj/ ./src/ ./tst/
rm -f .gitignore LICENSE
rm -f Makefile rerun
rm -f *.c *.sh

cd ../
echo "...Installation Done!"
