### Day 2 - Handle Event in Reason
***

I want to have a single component to handle all user events and fire a callback function as a props, which looks like:
`JSX
<EventLayer
  onGuesture=(reduce (fun movement => UserEvent movement))
/>
`

The argument of `reduce` function: `fun movement => UserEvent movement` just like action creator in redux. It tells us we want to dispatch a `UserEvent` action with a argument called `movement`, more about reducer compnent in ReasonReact can be found [here](https://reasonml.github.io/reason-react/docs/en/state-actions-reducer.html).

First we can have a look of render method in eventLayer.re, it is just another syntax of  `<div>{this.props.children}</div>`, but why not write in that way is a syntax problem of reason, which have explanation [here](https://reasonml.github.io/reason-react/docs/en/children.html):
` OCaml
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
`
