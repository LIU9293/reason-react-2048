![day1](https://github.com/LIU9293/reason-react-2048/raw/master/roadmap/day1_static_markup.png)

After some struggling, a easy static UI finally realize, and let's dive into this!
***

### Folder Structure
<img src="https://github.com/LIU9293/reason-react-2048/raw/master/roadmap/day1_folder_structure.png" style="margin: auto" />

Use the [reason-scripts](https://github.com/reasonml-community/reason-scripts), a tool just like create-react-app, we can easily setup a project easily without concerning about build configuration or some tough things. And I am very used to have a **components** folder for stateless UI components as well as a **containers** folder for business logic part. So far so good.

### First class files
Let's look inside index.re:

```ReasonML
[%bs.raw {|require('./index.css')|}];

external register_service_worker : unit => unit = "default" [@@bs.module "./registerServiceWorker"];

ReactDOMRe.renderToElementWithId <App message="Welcome to React and Reason" /> "root";

register_service_worker ();
```

There are no `import` or `export` actually, modules are shared by default, using the file name. (If you are familiar with React Native, RN has a `/* provideModule name */` way to make the build tool know it globally, Facebook style~).

But I find that files only under `src/` folder can be accessed, but files under `components/` folder cannot. After some search, that's caused be `bsconfig.json`(aka: BuckleScript Config) file. You must provide exactly what folders you want to use. And just change as following will be fine:

```JSON
"sources": [{
  "dir": "src",
  "subdirs": [
    "components",
    "containers"
  ]
}]
```

### React Component in Reason
So, we will have a `board` component, which is the main board and contains serval cards(tiles), and a `card` component, the card is really easy, following the [offcial guide](https://reasonml.github.io/reason-react/docs/en/creation-props-self.html), we just need a value prop and return a `div` contains a number. But at this time, you should take care because Reason is strong typed, so you cannot just add a string with a number anymore, you need something like `string_of_int`.
```OCaml
let component = ReasonReact.statelessComponent "Card";

let make ::value  _ => {
  ...component,
  render: fun _self =>
    if (value === 0) {
      <div className="card" />
    } else {
      <div className=("card card_number_" ^ (string_of_int value))>
        (ReasonReact.stringToElement (string_of_int value))
      </div>
    }
};
```

The one more difficult is the `board`, now I just want to pass a matrix and the board just show me the correct cards, the code looks like following:
```OCaml
let component = ReasonReact.statelessComponent "Board";
let originaState = [|
  [|0, 0, 0, 0|],
  [|0, 2, 0, 0|],
  [|0, 0, 2, 0|],
  [|0, 0, 0, 0|]
|];

let make _children => {
  // the function takes in an array of int, output an array of React Component
  let renderCells = fun row => {
    Array.mapi
      (fun index value =>
        <div className="cell" key=(string_of_int index)>
          <Card value=value />
        </div>
      )
      row
  };
  // below is the return, no return keyword here, just don't add ';'
  {
    ...component,
    render: fun _self => {
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
```
Now we just have a hardcoded prop, but it does render the correct thing we hope just like the image on top of this post. The syntax may looks strange to you but so do I, the language seems combine OCaml and JavaScript and modified JSX. But I believe you can understand it because I can understand as well.

So far so good. See you.
