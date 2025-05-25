File Renamer Script

This Bash script processes files in the input directory, renames them using a custom naming tool called namesmerizer, and saves the renamed copies in the output directory.
How It Works

    All files from the ./input/ directory are taken one by one.

    Each filename is passed to the namesmerizer tool, which outputs a new filename.

        Example:

        ./namesmerizer Adam_Kotłowski_242321.zip
        → 24321_Adam_Kotlowski.zip

    The file is then copied into the ./output/ directory with the new name.

Usage Instructions

    Make sure the following items are in place:

        A compiled or executable namesmerizer program in the current directory.

        An input/ folder containing the files to be processed.

        The script file (e.g., rename_files.sh) is executable.

    Run the script:

    ./rename_files.sh

    The renamed files will appear in the output/ directory.

Notes

    The script automatically creates the output/ folder if it doesn't exist.

    The namesmerizer must return a clean filename (no newline characters).

    The script handles filenames with special characters by sanitizing them using tr -d '\r\n'.
