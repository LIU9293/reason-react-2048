type action =
  | UserEvent EventLayer.movement
  | Failure
  | Restart
  | AddRandomCards;

type state = {
  board: array (array int),
  canUpdate: bool,
  timerId: ref (option Js.Global.timeoutId),
  failure: bool
};

let getInitState = {
  board: MoveLogic.initialBoard (),
  canUpdate: false,
  timerId: ref None,
  failure: false
};

let component = ReasonReact.reducerComponent "Controller";

let make _children => {
  ...component,
  initialState: fun _ => getInitState,
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
    | Failure => ReasonReact.Update {...state, canUpdate: false, failure: true}
    | Restart => ReasonReact.Update getInitState
    },
  didUpdate: fun {newSelf} =>
    if (MoveLogic.testFailure newSelf.state.board && newSelf.state.canUpdate) {
      newSelf.state.timerId :=
        Some (Js.Global.setTimeout (newSelf.reduce (fun _ => Failure)) 0)
    } else if
      newSelf.state.canUpdate {
      newSelf.state.timerId :=
        Some (
          Js.Global.setTimeout (newSelf.reduce (fun _ => AddRandomCards)) 100
        )
    },
  render: fun {state, reduce} => {
    let totalScore = MoveLogic.getTotalScore state.board;
    let highestScore = MoveLogic.getHighestScore state.board;
    <EventLayer
      onReplay=(reduce (fun _ => Restart))
      className="App"
      onGuesture=(reduce (fun movement => UserEvent movement))>
      <TitleArea totalScore highestScore />
      <Board board=state.board />
      <Notice />
      <Result
        failure=state.failure
        totalScore
        highestScore
        onReplay=(reduce (fun _ => Restart))
      />
    </EventLayer>
  }
};
