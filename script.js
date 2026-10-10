
const folders = [];
const files = [];

function createFolder() {
    const input = document.getElementById("folderName");
    const name = input.value.trim();

    if (name === "") {
        alert("Please enter a folder name!");
        return;
    }

    if (folders.includes(name)) {
        alert("Folder already exists!");
        return;
    }

    folders.push(name);
    input.value = "";
    displayItems();
}

function addFile() {
    const input = document.getElementById("fileName");
    const name = input.value.trim();

    if (name === "") {
        alert("Please enter a file name!");
        return;
    }

    if (files.includes(name)) {
        alert("File already exists!");
        return;
    }

    files.push(name);
    input.value = "";
    displayItems();
}

function displayItems() {
    const list = document.getElementById("itemList");
    list.innerHTML = "";

    folders.forEach(function(name) {
        const li = document.createElement("li");
        li.textContent = "📁 Folder: " + name;

        const button = document.createElement("button");
        button.textContent = "Delete";
        button.style.marginLeft = "10px";

        button.onclick = function() {
            const index = folders.indexOf(name);
            if (index !== -1) {
                folders.splice(index, 1);
                displayItems();
            }
        };

        li.appendChild(button);
        list.appendChild(li);
    });

    files.forEach(function(name) {
        const li = document.createElement("li");
        li.textContent = "📄 File: " + name;

        const button = document.createElement("button");
        button.textContent = "Delete";
        button.style.marginLeft = "10px";

        button.onclick = function() {
            const index = files.indexOf(name);
            if (index !== -1) {
                files.splice(index, 1);
                displayItems();
            }
        };

        li.appendChild(button);
        list.appendChild(li);
    });
}

function searchItem() {
    const name = document.getElementById("searchName")
        .value.trim().toLowerCase();

    const result = document.getElementById("searchResult");

    if (name === "") {
        result.textContent = "Please enter a name to search.";
        return;
    }

    const foundFolder = folders.some(
        folder => folder.toLowerCase() === name
    );

    const foundFile = files.some(
        file => file.toLowerCase() === name
    );

    if (foundFolder) {
        result.textContent = "Folder found: " + name;
    } else if (foundFile) {
        result.textContent = "File found: " + name;
    } else {
        result.textContent = "No file or folder found.";
    }
}
