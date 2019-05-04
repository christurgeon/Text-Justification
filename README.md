# Text-Justification
This program reads in a text file with text and takes command line arguments telling it to either left-align, right-align, or center-align the text. The aligned text is then written to a file.

## Command Line Arguments
```./a.out  INPUT_FILE  OUTPUT_FILE  TEXT_AREA_WIDTH  JUSTIFICATION_TYPE``` 

## Files
* ```INPUT_FILE``` is the text file that you want to read from.
* ```OUTPUT_FILE``` is the text file that you want to write the justified text to.

## Text Area Width 
The width of the text block that you want to create is given as a number in the ```TEXT_AREA_WIDTH``` location.

## Justification Types
Arguments for ```JUSTIFICATION_TYPE``` must be one of the following:
* ```flush_left```
* ```flush_right```
* ```full_justify```

