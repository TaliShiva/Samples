Build
-----
###### Установка зависимостей для сборки на Ubuntu 16.04:
```
sudo apt install software-properties-common
sudo add-apt-repository ppa:maarten-fonville/protobuf
sudo apt update
sudo apt install git build-essential cmake libprotobuf-dev protobuf-compiler libprotobuf10 libboost-all-dev bcache-tools
```
###### Сборка:
```
git clone https://gitlab.promobit.ru/core/single_controller_storage_system.git
cd single_controller_storage_system/
git submodule init
git submodule update
mkdir cmake-build-debug
cd cmake-build-debug/
cmake ..
make gorynych-control gorynych-admin
make gorynych-admin
```
###### Запуск
```
./gorynych-control
```
В другой консоли:
```
./gorynych-admin
```
