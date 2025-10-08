# MP3_TAG_READER
This project, **MP3 Tag Reader**, aims to create a software tool in **C** that can **read** and **edit** selected MP3 metadata (ID3v2.3 tags).  
It allows users to view and modify tags such as *Title, Artist, Album, Year, Genre,* and *Comments* directly from the terminal.

---

##  Features
-  View detailed MP3 tag information (ID3v2.3 format)  
-  Edit specific MP3 tags safely without corrupting the song file  
-  Validates MP3 files by checking the `ID3` signature  
-  Uses endian conversion to handle tag size correctly  
-  Modular code structure (`view`, `edit`, and `common` modules)  

---

##  Concepts Used
- File handling (binary mode)  
- Structures and dynamic memory allocation  
- Bitwise and byte-order manipulation  
- String handling (`strdup`, `strcmp`, `memcpy`)  
- Error handling and safe file operations  

---

##  Supported Tags
| Frame ID | Description        | Command Option |
|-----------|--------------------|----------------|
| `TIT2` | Song Title         | `-t` |
| `TPE1` | Artist Name        | `-a` |
| `TALB` | Album Name         | `-A` |
| `TYER` | Year of Release    | `-y` |
| `TCON` | Genre              | `-c` |
| `TCOM` | Composer / Comment | `-C` |

---

##  Compilation
Use GCC to compile all files:
```bash
gcc *.c -o mp3_reader
```
##  Future scopes
- upport for ID3v2.4 and higher tag versions
- Implement in-place editing without using a temporary file
- Add batch editing capability for multiple MP3 files
- Provide a GUI interface using GTK or Qt for visual tag editing
- Add support for album artwork (APIC frame) extraction and embedding
- Implement tag export/import to a .csv or .json file for backup
- Extend compatibility to Windows and Mac systems
-Integrate unit testing and logging for better maintainability
