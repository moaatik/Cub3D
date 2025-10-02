//! algo for parsing of cub3D maps:

//todo:
1 => check if the (.cub) file exist + have permission to read                     //! done !
    1.1 => make a get_next_line() fun	                                          //! done !
    1.2 => read line by line                                                      //! done !
    1.3 => check if this line is an instractions. else => error                   //! done !
2 => parse the instructions:
    2.1 => init the textures:
    2.2 => check if the path of every texture is correct + exist + read permission//! done !
    2.3 => set the texture path from the file to a struct                         //! done !
    2.4 => do the same with all (NO, SO, WE, EA)                                  //! done !
    2.5 => check if the RGB is ranged between 0 => 255 + just a 3 numbers + not 2 comas (not problem with wight spaces between them) //! done !
    2.6 => convert the RGB to int numbers (using betwise operators)               //! done !

3 => parse the map:
	3.1 => count the lenght + high of map to allocate enough space for it. (2D array)
		=> skip whitespaces at the end
		=> addvice => when you get the line using ft_strdup(). cut the '\n' from the end of the str
	3.1 => check if the bounds are closed by 1 or space //todo ( in progress )
		=> check the first + last line => they must be 1 or space
		=> check the border of map     => they must be 1
	3.2 => check if there is just 1 player
    3.1 => algo: loop over every ( 0 or player )character and check if the Neighbour char (up/down/left/right) of this 0 is not something else (1,0,player(N,S,W,E))
		=> check if there is forbbiden characters
		=> check if you found a \n after map and you found a nother line ( \n ) its error!
    3.2 => convert all spaces with 1 to make the map rectangular


	//todo: fix double instractions 
