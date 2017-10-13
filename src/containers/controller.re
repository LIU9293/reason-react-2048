type action =
  | UserEvent EventLayer.movement
  | AddRandomCards;

type state = {board: array (array int)};

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

let fillZero (array: array int) :array int => {
  let final = [|0, 0, 0, 0|];
  let len = Array.length array;
  for i in 0 to 3 {
    if (i < len) {
      final.(i) = array.(i)
    }
  };
  final
};

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
    let movedColumn = fillZero (addSame (clearZero column));
    let revertArray =
      Array.mapi (fun index _ => movedColumn.(3 - index)) movedColumn;
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
  Array.map
    (
      fun value => {
        let arr = fillZero (addSame (clearZero value));
        Array.mapi (fun index _ => arr.(3 - index)) arr
      }
    )
    board;

let component = ReasonReact.reducerComponent "Controller";

let make _children => {
  ...component,
  initialState: fun () => {
    board: [|[|2, 0, 0, 0|], [|0, 2, 0, 0|], [|2, 0, 2, 0|], [|0, 0, 0, 0|]|]
  },
  reducer: fun action state =>
    switch action {
    | UserEvent movement =>
      switch movement {
      | Up => ReasonReact.Update {board: transformUp state.board}
      | Down => ReasonReact.Update {board: transformDown state.board}
      | Right => ReasonReact.Update {board: transformRight state.board}
      | Left => ReasonReact.Update {board: transformLeft state.board}
      | None => ReasonReact.NoUpdate
      }
    | AddRandomCards => ReasonReact.NoUpdate
    },
  render: fun self =>
    <EventLayer
      className="App"
      onGuesture=(self.reduce (fun movement => UserEvent movement))>
      <div className="App-header">
        <h2> (ReasonReact.stringToElement "ReasonReact 2048") </h2>
      </div>
      <Board board=self.state.board />
    </EventLayer>
};
