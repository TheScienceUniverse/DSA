prj_dir=$(pwd)
cd ../

if [ ! -d "./DSA/.git/" ]
then
	cd ./DSA/
	echo "Updating DSA project..."
	git pull origin master
	cd ../
else
	echo "Fetching DSA project..."
	git clone https://github.com/TheScienceUniverse/DSA.git --branch origin/master --single-branch --depth 1
fi;

cd ./DSA/

echo "Setting up directories..."
mkdir -p ./obj/ ./lib/ ./bin/

echo "Building library..."
make again

echo "Creating log directory (DON'T DELETE)..."
mkdir -p ../log/
#cp ./inc/* ../inc/
#cp ./lib/libdsa.so ../lib/

echo "Cleaning up...";
#rm -rf ./.git/ ./.github/ ./aft/ ./bin/ ./cov/ ./doc/ ./font/ ./log/ ./media/ ./obj/ ./src/ ./tst/
#rm -f .gitignore LICENSE
#rm -f Makefile rerun
#rm -f *.c *.sh

cd $(prj_dir)
echo "...Installation Done!"
