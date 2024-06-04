from cs50 import get_int


def main():
    getheight()

# we define a function for this because it's an easy way to ask again
# for a height if the previously given height was invalid.


def getheight():
    height = get_int("Height: ")
    # if the height isn't valid, run the function again.
    if height > 8 or height < 1:
        getheight()
    else:  # we can only get to this else if the height given is a valid one,
        # so no more validation is needed.
        for i in range(height):  # looping as many times as the height
            row = ""  # since python automatically adds the \n character to the
            # end of print's, unlike C, we have to instead define an
            # empty string,then concatenate the desired characters
            # until we finally print the row at the end of the loop.
            for c in range(height-i-1):
                row = row + " "
            for a in range(i+1):
                row = row + "#"
            row = row + "  "
            for b in range(i+1):
                row = row + "#"
            print(row)


# finally, we call main to run the program.
main()
