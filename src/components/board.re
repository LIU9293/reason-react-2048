[%bs.raw {|require('./board.css')|}];

let component = ReasonReact.statelessComponent "Board";

let make ::board _children => {
  let renderCells cellArray =>
    Array.mapi
      (
        fun index value =>
          <div className="cell" key=(string_of_int index)>
            <Card value />
          </div>
      )
      cellArray;
  {
    ...component,
    render: fun _self => {
      let rows =
        Array.mapi
          (
            fun index _ =>
              <div className="row" key=(string_of_int index)>
                (ReasonReact.arrayToElement (renderCells board.(index)))
              </div>
          )
          [|1, 2, 3, 4|];
      <div className="game-area">
        <div className="board"> (ReasonReact.arrayToElement rows) </div>
      </div>
    }
  }
};
