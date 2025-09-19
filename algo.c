//! algo for parsing of cub3D maps:

//todo:
1 => check if the (.cub) file exist + have permission to read
2 => parse the instructions:
    2.1 => init the textures:
    2.2 => check if the path of every texture is correct + exist + read permission
    2.3 => set the texture from the file to a struct
    2.4 => do the same with all (NO, SO, WE, EA)
    2.5 => check if the RGB is ranged between 0 => 255 + just a 3 numbers + not 2 comas (not problem with wight spaces between them)
    2.6 => convert the RGB to int numbers (using betwise operators)

3 => parse the map:
    3.1 => algo: loop over every 0 character and check if the Neighbour char (up/down/left/right) of this 0 is not something else (1,0,player(N,S,W,E))
    3.2 => convert all spaces with 1 to make the map rectangular

4 => 
5 => 
