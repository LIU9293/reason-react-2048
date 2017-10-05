[%bs.raw {|require('./board.css')|}];

let component = ReasonReact.statelessComponent "Board";
let originaState = [|
  [|0, 0, 0, 0|],
  [|0, 2, 0, 0|],
  [|0, 0, 2, 0|],
  [|0, 0, 0, 0|]
|];

let make _children => {
  let renderCells = fun cellArray => {
    Array.mapi
      (fun index value =>
        <div className="cell" key=(string_of_int index)>
          <Card value=value />
        </div>
      )
      cellArray
  };
  {
    ...component,
    render: fun self => {
      let rows = {
        Array.mapi
          (fun index _ =>
            <div className="row" key=(string_of_int index)>
              (ReasonReact.arrayToElement (renderCells originaState.(index)))
            </div>
          )
          [|1, 2, 3, 4|]
      };
      <div className="board">
        (ReasonReact.arrayToElement rows)
      </div>
    }
  }
};
