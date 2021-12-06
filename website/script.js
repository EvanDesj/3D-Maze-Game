/* eslint-disable no-unused-vars */
let globalSize = 12;
let playBoard = [];

const table = document.getElementById('myTable');

const renderBoard = () => {
  table.innerHTML = '<table id="myTable"></table>';
  playBoard.forEach((column, ci) => {
    const row = table.insertRow(ci);
    column.forEach((e, i) => {
      const cell = row.insertCell(i);
      if (e === 1) {
        cell.innerHTML = `<p id="block_${i}" class="block occupied" onclick="interactTile(${ci},${i})">${playBoard[ci][i]}</p>`;
      } else {
        cell.innerHTML = `<p id="block_${i}" class="block" onclick="interactTile(${ci},${i})">${playBoard[ci][i]}</p>`;
      }
    });
  });
};

function generateBoard() {
  playBoard = [];
  let i = 0;
  while (i <= globalSize) {
    playBoard[i] = [];
    for (let index = 0; index < globalSize; index += 1) {
      playBoard[i].push(0);
    }
    i += 1;
  }
}

function updateNumbers() {
  let max = document.getElementById('number').value;
  if (!max || max < 3) {
    max = 3;
  }
  globalSize = max;
  document.getElementById('number').value = max;
  generateBoard();
  renderBoard();
}

function interactTile(c, i) {
  if (playBoard[c][i] === 0) {
    playBoard[c][i] = 1;
  } else {
    playBoard[c][i] = 0;
  }
  renderBoard();
}

function exportBoard() {
  const boardRaw = JSON.stringify(playBoard);
  let board = '';
  Object.values(boardRaw).forEach((value) => {
    let text = value;
    if (value === '[') {
      text = '{';
    }
    if (value === ']') {
      text = '}';
    }
    board += text;
  });
  const blob = new Blob([board], { type: 'text/plain' });
  const url = URL.createObjectURL(blob);
  const a = document.createElement('a');
  a.href = url;
  a.download = 'board.txt';
  a.click();
  URL.revokeObjectURL(url);
}

function importBoard() {
  const file = document.getElementById('file').files[0];
  const reader = new FileReader();
  reader.readAsText(file);
  let uploadedBoard = '';
  reader.onload = (event) => {
    const text = event.target.result;
    Object.values(text).forEach((char) => {
      if (char === '{') {
        uploadedBoard += '[';
      } else if (char === '}') {
        uploadedBoard += ']';
      } else {
        uploadedBoard += char;
      }
    });
    playBoard = JSON.parse(uploadedBoard);
    globalSize = playBoard.length;
    // console.log(playBoard);
    renderBoard();
  };
}

const resetBoard = () => {
  generateBoard();
  renderBoard();
};

resetBoard();
