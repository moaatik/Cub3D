//! algo for parsing of cub3D maps:

1 => check if the (.cub) file exist + have permission to read                     //! done !
    1.1 => make a get_next_line() fun	                                          //! done !
    1.2 => read line by line                                                      //! done !
    1.3 => check if this line is an instractions. else => error                   //! done !

2 => parse the instructions:
    2.1 => init the textures:                                                     //todo
    2.2 => check if the path of every texture is correct + exist + read permission//! done !
    2.3 => set the texture path from the file to a struct                         //! done !
    2.4 => do the same with all (NO, SO, WE, EA)                                  //! done !
    2.5 => check if the RGB is ranged between 0 => 255 + just a 3 numbers + not 2 comas (no problem with wight_spaces between them) //! done !
    2.6 => convert the RGB to int numbers (using betwise operators)               //! done !

3 => parse the map:
	3.1 => count the lenght + high of map to allocate enough space for it. (2D array) //! done !
		=> skip whitespaces at the end                                                //! done !
		=> addvice => when you get the line using ft_strdup(). cut the '\n' from the end of the str //! done !
	3.1 => check the first + last line => they must be '1' or space                   //! done !
		=> check the border of map     => they must be '1'                            //! done !
	3.2 => check if there is just 1 player                                            //! done !
    3.1 => algo: loop over every '0' char and check if the Neighbour char (up/down/left/right) of this '0' is not something else (1,0) //! done !
		=> check if there is forbbiden characters                                     //! done !
		=> check if you found a '\n' after map and you found a nother line ( '\n' ) its error! //! done !
    3.2 => convert all spaces with 1 to make the map rectangular                      //! done !
	3.3 => sotre the height + width of map                                            //! done !

4 => Initialize MLX and load textures
	=> Initialize MLX                                                                 //todo
	=> Load your textures                                                             //todo

=> //todo: check if you close the fd every time you exit!
=> make a small gabage fds like the ft_safe_malloc() but this time for fds           //! done !
