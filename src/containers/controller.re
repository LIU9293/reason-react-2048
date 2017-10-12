
type action =
  | OnTouchStart ReactEventRe.Touch.t
  | OnTouchEnd ReactEventRe.Touch.t;

type state = {
  startX: int,
  startY: int
};

let component = ReasonReact.reducerComponent "Controller";

let onGuesture = fun (gusture) => {
  Js.log gusture;
};

let make _children => {
  ...component,
  initialState: fun () => {
    startX: 0,
    startY: 0
  },
  reducer: fun action state =>
    switch action {
    | OnTouchStart event => {
        ReactEventRe.Touch.persist event;
        let nativeEvent = ReactEventRe.Touch.nativeEvent event;
        Js.log nativeEvent;
        ReactEventRe.Touch.persist event;
        ReasonReact.NoUpdate
      }
    | OnTouchEnd event => {
        Js.log (ReactDOMRe.domElementToObj (ReactEventRe.Touch.target event));
        ReasonReact.NoUpdate
      }
    },
  render: fun self =>
    <EventLayer
      className="App"
      onGuesture=onGuesture
    >
      <div className="App-header">
        <h2> (ReasonReact.stringToElement "ReasonReact 2048") </h2>
      </div>
      <div> (ReasonReact.stringToElement (string_of_int self.state.startY)) </div>
      <Board />
    </EventLayer>
};
