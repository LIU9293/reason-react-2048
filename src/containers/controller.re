type action =
  | UserEvent EventLayer.movement
  | AddRandomCards;

type state = {
  board: array (array int)
};

let addSame = fun (array: array int) : array int => {
  let len = Array.length array;
  Js.log len;
  if (len === 4 && array.(0) === array.(1) && array.(2) === array.(3)) {
    [| array.(0) * 2, array.(2) * 2 |]
  } else {
    for i in 0 to 3 {
      if (array.(i) === array.(i + 1)) {
        Array.append
          Array.sub (array 0 i)
          [| array[i] * 2 |]
          Array.sub (array i + 2)
      } else {
        array
      };
    };
  };
  /* for i in 0 to 3 {
    if (array.(i) === array.(i + 1)) {
      a = Array.concat
            Array.sub (array 0 i)
            [| array[i] * 2 |]
            Array.sub (array i + 2)
    };
  }; */

};

let component = ReasonReact.reducerComponent "Controller";

let make _children => {
  ...component,
  initialState: fun () => {
    board: [|
      [|0, 0, 0, 0|],
      [|0, 2, 0, 0|],
      [|0, 0, 2, 0|],
      [|0, 0, 0, 0|]
    |]
  },
  reducer: fun action state =>
    switch action {
    | UserEvent movement => {
        switch movement {
          | Up => {
              Js.log (addSame [| 2, 2, 4, 4 |]);
              ReasonReact.NoUpdate
            }
          | Down => ReasonReact.NoUpdate
          | Right => ReasonReact.NoUpdate
          | Left => ReasonReact.NoUpdate
          | None => ReasonReact.NoUpdate
        }
      }
    | AddRandomCards => {
        ReasonReact.NoUpdate
      }
    },
  render: fun self =>
    <EventLayer
      className="App"
      onGuesture=(self.reduce (fun movement => UserEvent movement))
    >
      <div className="App-header">
        <h2> (ReasonReact.stringToElement "ReasonReact 2048") </h2>
      </div>
      <Board board=self.state.board />
    </EventLayer>
};
