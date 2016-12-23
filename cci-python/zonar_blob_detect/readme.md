instructions were ambiguous on a couple of points , probably intentionally:
    - not consistent whether using '0'(zero) or 'O'(capital o) : used capital o
    - not consistent with definition of blob-says blobs are contiguous tokens
      then shows example of single token as 'blob' with count of 1 , i.e .
      by this definition , the X's ollowing  are not 'touching' despite the comments:
        0 X 0
        0 0 X
        0 0 0
      and by this definiton a 'blob' cannot have a count of 1(a token cannot be
      'contiguous' to itself).

      Went with contiguous definition..


run:
    python3 zn_blob_detect.py zb_data
test:
    python3 zbd_test.py
tested on:
    Linux 3.19.0-32-generic #37~14.04.1-Ubuntu SMP i686 i686 i686 GNU/Linux
    Python 3.4.3

William K. Johnson
12/16/2016
