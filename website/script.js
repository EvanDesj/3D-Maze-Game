/* eslint-disable no-unused-vars */
let globalSize = 24;
const defaultBoard = [[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
[1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1],
[1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1],
[1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1],
[1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1],
[1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1],
[1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1],
[1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1],
[1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1],
[1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1],
[1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1],
[1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1],
[1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1],
[1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1],
[1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1],
[1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1],
[1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1],
[1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1],
[1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1],
[1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1],
[1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1],
[1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1],
[1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1],
[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]];
let playBoard = defaultBoard.slice();

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
  while (i < globalSize) {
    playBoard[i] = [];
    for (let index = 0; index < globalSize; index += 1) {
      playBoard[i].push(0);
    }
    i += 1;
  }
  document.getElementById('edges').innerHTML = 'Fill Edges';
}

function updateNumbers() {
  let max = document.getElementById('number').value;
  if (!max || max < 3) {
    max = 3;
  }
  if (max > 50) {
    max = 50;
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
  if (!file) {
    return;
  }
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
    document.getElementById('number').value = globalSize;
    renderBoard();
  };
}

function selectEdges() {
  const checked = document.getElementById('edges').innerHTML === 'Fill Edges';
  const first = 0;
  const last = playBoard.length - 1;
  let current = first;
  while (current <= last) {
    for (let index = 0; index < playBoard[current].length; index += 1) {
      if (
        checked
        && (current === 0
          || current === last
          || index === 0
          || index === playBoard[current].length - 1)
      ) {
        playBoard[current][index] = 1;
      } else if (
        current === 0
        || current === last
        || index === 0
        || index === playBoard[current].length - 1
      ) {
        playBoard[current][index] = 0;
      }
    }
    current += 1;
  }
  if (checked) {
    document.getElementById('edges').innerHTML = 'Clear Edges';
  } else {
    document.getElementById('edges').innerHTML = 'Fill Edges';
  }
  renderBoard();
}

const resetBoard = () => {
  generateBoard();
  renderBoard();
};

const loadDefaultBoard = () => {
  playBoard = defaultBoard.slice();
  globalSize = playBoard.length;
  document.getElementById('number').value = globalSize;
  renderBoard();
};

renderBoard();
