let addSame (array: array int) :array int => {
  let len = Array.length array;
  let final = ref array;
  let i = ref 0;
  if (len === 4 && array.(0) === array.(1) && array.(2) === array.(3)) {
    [|array.(0) * 2, array.(2) * 2|]
  } else {
    while (!i < len - 1) {
      if (array.(!i) === array.(!i + 1)) {
        let first = Array.sub array 0 !i;
        let last = Array.sub array (!i + 2) (Array.length array - !i - 2);
        final := Array.append (Array.append first [|array.(!i) * 2|]) last;
        i := 3
      } else {
        i := !i + 1
      }
    };
    !final
  }
};

let clearZero (array: array int) :array int => {
  let final = ref [||];
  for i in 0 to 3 {
    if (array.(i) !== 0) {
      final := Array.append !final [|array.(i)|]
    }
  };
  !final
};

let fillZero (array: array int) :array int =>
  Array.append array (Array.make (4 - Array.length array) 0);

let fillZeroLeft (array: array int) :array int =>
  Array.append (Array.make (4 - Array.length array) 0) array;

let transformUp (board: array (array int)) :array (array int) => {
  let next = [|
    [|0, 0, 0, 0|],
    [|0, 0, 0, 0|],
    [|0, 0, 0, 0|],
    [|0, 0, 0, 0|]
  |];
  let nextN = [|
    [|0, 0, 0, 0|],
    [|0, 0, 0, 0|],
    [|0, 0, 0, 0|],
    [|0, 0, 0, 0|]
  |];
  for i in 0 to 3 {
    let column = Array.map (fun value => value.(i)) board;
    let movedColumn = fillZero (addSame (clearZero column));
    next.(i) = movedColumn
  };
  for i in 0 to 3 {
    let col = Array.map (fun value => value.(i)) next;
    nextN.(i) = col
  };
  nextN
};

let transformDown (board: array (array int)) :array (array int) => {
  let next = [|
    [|0, 0, 0, 0|],
    [|0, 0, 0, 0|],
    [|0, 0, 0, 0|],
    [|0, 0, 0, 0|]
  |];
  let nextN = [|
    [|0, 0, 0, 0|],
    [|0, 0, 0, 0|],
    [|0, 0, 0, 0|],
    [|0, 0, 0, 0|]
  |];
  for i in 0 to 3 {
    let column = Array.map (fun value => value.(i)) board;
    let revertColumn = Array.mapi (fun index _ => column.(3 - index)) column;
    let movedArry = fillZero (addSame (clearZero revertColumn));
    let revertArray =
      Array.mapi (fun index _ => movedArry.(3 - index)) movedArry;
    next.(i) = revertArray
  };
  for i in 0 to 3 {
    let col = Array.map (fun value => value.(i)) next;
    nextN.(i) = col
  };
  nextN
};

let transformLeft (board: array (array int)) :array (array int) =>
  Array.map (fun value => fillZero (addSame (clearZero value))) board;

let transformRight (board: array (array int)) :array (array int) =>
  Array.map (fun value => fillZeroLeft (addSame (clearZero value))) board;

let randomAddCard (board: array (array int)) :array (array int) => {
  let zeroLocationMap = ref [||];
  let random = ref 0;
  let nextCard = [|2, 2, 4, 2, 2|];
  let u =
    Array.mapi
      (
        fun rowIndex row =>
          Array.mapi
            (
              fun columnIndex cell =>
                if (cell === 0) {
                  zeroLocationMap :=
                    Array.append !zeroLocationMap [|[|rowIndex, columnIndex|]|]
                }
            )
            row
      )
      board;
  let zeroLocationMapValue = !zeroLocationMap;
  if (Array.length zeroLocationMapValue === 0) {
    board
  } else {
    Random.init [%bs.raw {|Math.random() * 10000|}];
    if (Array.length zeroLocationMapValue <= 1) {
      random := 0
    } else {
      random := Random.int (Array.length zeroLocationMapValue - 1)
    };
    let targetCell = zeroLocationMapValue.(!random);
    let final = board;
    let nextRandomNumber = nextCard.(Random.int 4);
    final.(targetCell.(0)).(targetCell.(1)) = nextRandomNumber;
    final
  }
};

let initialBoard () => {
  let board = [|
    [|0, 0, 0, 0|],
    [|0, 0, 0, 0|],
    [|0, 0, 0, 0|],
    [|0, 0, 0, 0|]
  |];
  randomAddCard (randomAddCard (randomAddCard board))
};

let getTotalScore (board: array (array int)) :int => {
  let total = ref 0;
  for i in 0 to 3 {
    for j in 0 to 3 {
      total := !total + board.(i).(j)
    }
  };
  !total
};

let getHighestScore (board: array (array int)) :int => {
  let highest = ref 0;
  for i in 0 to 3 {
    for j in 0 to 3 {
      if (!highest < board.(i).(j)) {
        highest := board.(i).(j)
      }
    }
  };
  !highest
};

let noZero (board: array (array int)) :bool => {
  let final = ref true;
  for i in 0 to 3 {
    for j in 0 to 3 {
      if (board.(i).(j) === 0) {
        final := false
      }
    }
  };
  !final
};

let testFailure (board: array (array int)) :bool => {
  let final = ref true;
  if (noZero board) {
    for i in 0 to 3 {
      for j in 0 to 2 {
        if (board.(i).(j) === board.(i).(j + 1)) {
          final := false
        } else if (
          board.(j).(i) === board.(j + 1).(i)
        ) {
          final := false
        }
      }
    };
    !final
  } else {
    false
  }
};
