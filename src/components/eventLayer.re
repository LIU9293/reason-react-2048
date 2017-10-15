type event = {
  mutable startX: int,
  mutable startY: int,
  mutable endX: int,
  mutable endY: int,
  mutable timestampStart: int,
  mutable timestampEnd: int
};

type element;

let document: element = [%bs.raw "document"];

type movement =
  | Up
  | Down
  | Right
  | Left
  | None;

let eventRecorder = {
  startX: 0,
  startY: 0,
  endX: 0,
  endY: 0,
  timestampStart: 0,
  timestampEnd: 0
};

external addEventListener :
  element => string => (ReactEventRe.Keyboard.t => unit) => unit =
  "addEventListener" [@@bs.send];

let getGusture () :movement => {
  let gusture = ref None;
  let min = 4000;
  let {startX, startY, endX, endY, timestampStart, timestampEnd} = eventRecorder;
  let speedDown = (endY - startY) * 10000 / (timestampEnd - timestampStart);
  let speedRight = (endX - startX) * 10000 / (timestampEnd - timestampStart);
  if (
    (speedDown > 0 ? speedDown : - speedDown)
    > (speedRight > 0 ? speedRight : - speedRight)
  ) {
    if (speedDown - min > 0) {
      gusture := Down
    };
    if (speedDown + min < 0) {
      gusture := Up
    }
  } else {
    if (speedRight - min > 0) {
      gusture := Right
    };
    if (speedRight + min < 0) {
      gusture := Left
    }
  };
  !gusture
};

let component = ReasonReact.statelessComponent "EventLayer";

let make ::className=? ::onGuesture children => {
  let onTouchStart event => {
    let touch = (ReactEventRe.Touch.nativeEvent event)##targetTouches;
    eventRecorder.startX = touch.(0)##screenX;
    eventRecorder.startY = touch.(0)##screenY;
    eventRecorder.timestampStart = [%bs.raw {|new Date().getTime()|}]
  };
  let onTouchEnd event => {
    let touch = (ReactEventRe.Touch.nativeEvent event)##changedTouches;
    eventRecorder.endX = touch.(0)##screenX;
    eventRecorder.endY = touch.(0)##screenY;
    eventRecorder.timestampEnd = [%bs.raw {|new Date().getTime()|}];
    onGuesture (getGusture ())
  };
  let onKeyDown event => {
    let code = ReactEventRe.Keyboard.keyCode event;
    if (code === 37) {
      onGuesture Left
    } else if (code === 38) {
      onGuesture Up
    } else if (
      code === 39
    ) {
      onGuesture Right
    } else if (
      code === 40
    ) {
      onGuesture Down
    } else {
      onGuesture None
    }
  };
  {
    ...component,
    didMount: fun _ => {
      addEventListener document "keydown" onKeyDown;
      ReasonReact.NoUpdate
    },
    render: fun _self =>
      ReasonReact.createDomElement
        "div"
        props::{
          "onTouchStart": onTouchStart,
          "onTouchEnd": onTouchEnd,
          "className": className
        }
        children
  }
};
