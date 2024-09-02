# Parallel-Number-Classification
 
Just got to start the container with the following command
```
docker-compose run --build --rm -it development
```
## How to run?
### Sequential
To compile the sequential program, run the following command
```bash
g++ -o sort_sequential sort_sequential.cpp
```
Then run it with the following command and add the path to the csv file
```bash
./sort_sequential <csv_path>
```
If you ran the Docker container, then you can run the following command
```bash
./sort_sequential numbers.csv
```
### Parallel
To compile the parallel program, run the following command
```bash
g++ -fopenmp -o sort_sequential_omp sort_sequential_omp.cpp
```
Then run it with the following command and add the path to the csv file
```bash
./sort_sequential <csv_path>
```
If you ran the Docker container, then you can run the following command
```bash
./sort_sequential_omp numbers.csv
```