## Ray Tracer

- Build
    - `make all`
- Run
    - `./main <input_path> <sample_size>`
    - Ex:
        - With defaults         `./main test2.in` 
        - With Sample Size (AA) `./main test2refractive.in 4` 
        
### Extras:
- Reflection
- Refraction
- Antialising (see examples to set sample size)

### Notes:
- Colors doesn't match perfectly to the test cases. By dividing `phong (see light.cpp)` parameters to 
some magic numbers, similar colors achievable. But I left it as it is. 


