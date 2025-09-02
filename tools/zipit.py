import sys
import zipfile
def zipthis(*filepaths: str,zip_filepath: str):
    """Creates a zip archive from a list of files.

    This function takes an arbitrary number of file paths and compresses
    them into a single zip archive. The final zip file is named using the
    `zip_filepath` parameter. It adds the files to the root of the zip
    archive, checking for duplicate filenames to prevent overwriting.

    Args:
        *filepaths: One or more string arguments representing the paths
                    to the files that should be added to the zip file.
        zip_filepath: The desired name of the output zip file.

    Raises:
        NameError: If a duplicate filename is found among the input file paths.
    """
    doubles = set()
    with zipfile.ZipFile(f'{zip_filepath}','w') as ZIP:
        for from_ in filepaths:
            
            ffrom = from_.replace('\\','/')
            if ffrom in doubles:
                raise NameError(f"Duplicate file name found: '{to}'. Each file must have a unique name inside the zip archive.")
            to = ffrom.split('/')[-1]
            doubles.add(to)
            ZIP.write(from_,to)
            
if __name__ == '__main__':
    if len(sys.argv) == 2:
        print(zipthis.__doc__)
    if len(sys.argv) < 4:
        raise SyntaxError("Provide at least {zip_filepath} & one file that should be zipped!")
    zfp, *fp = sys.argv[1:]
    
    zipthis(*fp,zip_filepath=zfp)