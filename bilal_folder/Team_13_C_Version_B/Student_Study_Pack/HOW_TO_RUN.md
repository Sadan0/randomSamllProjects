# HOW TO RUN — C

### Requirements
- Windows PC
- MinGW/GCC installed and available in PATH
- Google Chrome

### Steps
1. Open this folder in VS Code.
2. Open Terminal in this folder.
3. Compile the server:

```bash
gcc server.c -lws2_32 -o server.exe
```

4. Run it:

```bash
server.exe
```

5. Open Google Chrome.
6. Visit:

`http://localhost:5000`

### Stop the server
Press `Ctrl + C` in the terminal.
