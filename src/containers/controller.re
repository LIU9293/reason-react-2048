type action =
  | UserEvent EventLayer.movement
  | AddRandomCards;

type state = {
  board: array (array int),
  canUpdate: bool,
  timerId: ref (option Js.Global.timeoutId)
};

let component = ReasonReact.reducerComponent "Controller";

let make _children => {
  ...component,
  initialState: fun () => {
    board: [|[|2, 0, 0, 0|], [|0, 2, 0, 0|], [|2, 0, 2, 0|], [|0, 0, 0, 0|]|],
    canUpdate: true,
    timerId: ref None
  },
  reducer: fun action state =>
    switch action {
    | UserEvent movement =>
      switch movement {
      | Up =>
        ReasonReact.Update {
          ...state,
          canUpdate: true,
          board: MoveLogic.transformUp state.board
        }
      | Down =>
        ReasonReact.Update {
          ...state,
          canUpdate: true,
          board: MoveLogic.transformDown state.board
        }
      | Right =>
        ReasonReact.Update {
          ...state,
          canUpdate: true,
          board: MoveLogic.transformRight state.board
        }
      | Left =>
        ReasonReact.Update {
          ...state,
          canUpdate: true,
          board: MoveLogic.transformLeft state.board
        }
      | None => ReasonReact.NoUpdate
      }
    | AddRandomCards =>
      ReasonReact.Update {
        ...state,
        board: MoveLogic.randomAddCard state.board,
        canUpdate: false
      }
    },
  didUpdate: fun {newSelf} =>
    if newSelf.state.canUpdate {
      newSelf.state.timerId :=
        Some (
          Js.Global.setTimeout (newSelf.reduce (fun _ => AddRandomCards)) 150
        )
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
