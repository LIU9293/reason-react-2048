type event = {
  mutable startX: int,
  mutable startY: int,
  mutable endX: int,
  mutable endY: int,
  mutable timestampStart: int,
  mutable timestampEnd: int
};

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

let getGusture = fun () :movement => {
  let gusture = ref None;
  let min = 4000;
  let { startX, startY, endX, endY, timestampStart, timestampEnd } = eventRecorder;
  let speedDown = (endY - startY) * 10000 / (timestampEnd - timestampStart);
  let speedRight = (endX - startX) * 10000 / (timestampEnd - timestampStart);
  if ((speedDown > 0 ? speedDown : -speedDown) > (speedRight > 0 ? speedRight : -speedRight)) {
    if ( speedDown - min > 0) {
      gusture := Down;
    };
    if ( speedDown + min < 0) {
      gusture := Up;
    };
  } else {
    if ( speedRight - min > 0 ) {
      gusture := Right;
    };
    if ( speedRight + min < 0 ) {
      gusture := Left;
    };
  };
  !gusture
};

let component = ReasonReact.statelessComponent "EventLayer";

let make ::className=? ::onGuesture children => {
  let onTouchStart = fun event _self => {
    let touch = (ReactEventRe.Touch.nativeEvent event)##targetTouches;
    eventRecorder.startX = touch.(0)##screenX;
    eventRecorder.startY = touch.(0)##screenY;
    eventRecorder.timestampStart = [%bs.raw {|new Date().getTime()|}];
  };
  let onTouchEnd  = fun event _self => {
    let touch = (ReactEventRe.Touch.nativeEvent event)##changedTouches;
    eventRecorder.endX = touch.(0)##screenX;
    eventRecorder.endY = touch.(0)##screenY;
    eventRecorder.timestampEnd = [%bs.raw {|new Date().getTime()|}];
    onGuesture (getGusture ());
  };
  {
    ...component,
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
