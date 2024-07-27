#ifndef LZ77ENCODER_H_INCLUDED
#define LZ77ENCODER_H_INCLUDED

/*Update look ahead buffer from the original file by finding the number of empty space in it
*
*Parameter
*lab		look ahead buffer char array
*test		original text char array
*lab_Len	length of current look ahead buffer
*buf_Size	buffer size
*empty		empty spaces in the look ahead buffer
*test_Len	length of original text file
*No Return value
*Just updates the look ahead buffer
*/
void lab_upd();

/*Update search buffer and look ahead buffer from the output tuple of the longest match found
*
*Parameter
*sb			search buffer char array
*lab		look ahead buffer char array 
*mtch_Len	length of longest match 
*len		summation of all prev (longest_match(l)+1) (<o,l,c()>)
*buf_Size	buffer size
*test_Len	length of original text file
*No Return value
*Just updates the look ahead buffer  and search buffer
*/

void buf_upd();

/*Searching in search buffer to find longest match of the look-ahead buffer and generating the output tuple
*
*Parameter
*sb			search buffer char array
*lab		look ahead buffer char array 
*len_sb		length of search buffer
*len_Lab	length of look ahead buffer
*ch			initial character value for starting search
*offset		offset of the longest match found
*length		length of the longest match found	
*luc		last unmatched character of the longest match found
*mtch_Len	length of longest match 
*len		summation of all prev (longest_match(l)+1) (<o,l,c()>)
*buf_Size	buffer size
*test_Len	length of original text file
*No Return value
*Just writes the output tuple( <offset,length,last unmatched char> ) in the compressed file
*/

void seq_sb();

/*Package function which calls the above functions in the order (lab_upd->seq_sb->buf_upd->lab_upd)
*
*Parameter
*lab_Len	length of look ahead buffer for checking loop termination condition (lab_Len!=0)
*No Return value
*Calls the above function to compress the original text
*/

void encoder();

#endif
