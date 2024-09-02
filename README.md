# Parallel-Number-Classification
 
Just got to start the container with the following command
```
docker-compose run --build --rm -it development
```

To compile the program, run the following command
```bash
g++ -o sort_sequential sort_sequential.cpp
```
Then run it with the following command and add the path to the csv file
```bash
./sort_sequential <csv_path>
```