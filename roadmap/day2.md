### Day 2 - Handle Event in Reason
***

I want to have a single component to handle all user events and fire a callback function as a props, which looks like:
`JSX
<EventLayer
  onGuesture=(reduce (fun movement => someMethods movement))
/>
`

The argument of `reduce` function: `fun movement => UserEvent movement` just like action creator in redux. It tells us we want to dispatch a `UserEvent` action with a argument called `movement`, more about reducer compnent in ReasonReact can be found [here](https://reasonml.github.io/reason-react/docs/en/state-actions-reducer.html).

First we can have a look of render method in eventLayer.re, it is just another syntax of  `<div>{this.props.children}</div>`, but why not write in that way is a syntax problem of reason, which have explanation [here](https://reasonml.github.io/reason-react/docs/en/children.html):
```OCaml
render: fun _self =>
  ReasonReact.createDomElement
    "div"
    props::{
      "onTouchMove": onTouchMove,
      "onTouchStart": onTouchStart,
      "onTouchEnd": onTouchEnd,
      "className": className
    }
    children
```

So, we just want to record the touch event, and here I used a record with mutable fields to record the changes of the event target:
```OCaml
type event = {
  mutable startX: int,
  mutable startY: int,
  mutable endX: int,
  mutable endY: int,
  mutable timestampStart: int,
  mutable timestampEnd: int
};
let eventRecorder = {
  startX: 0,
  startY: 0,
  endX: 0,
  endY: 0,
  timestampStart: 0,
  timestampEnd: 0
};
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
  onGuesture (getGusture ()) // pass the gusture to the props callback function
};
```
