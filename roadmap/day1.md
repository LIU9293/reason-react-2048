![day1]('https://github.com/LIU9293/reason-react-2048/raw/master/roadmap/day1_static_markup.png')

After some struggling, a easy static UI finally realize, and let's dive into this!
***

### Folder Structure
![folder]('https://github.com/LIU9293/reason-react-2048/raw/master/roadmap/day1_folder_structure.png')
Use the [reason-scripts](https://github.com/reasonml-community/reason-scripts), a tool just like create-react-app, we can easily setup a project easily without concerning about build configuration or some tough things. And I am very used to have a **components** folder for stateless UI components as well as a **containers** folder for business logic part. So far so good.

### First class files
Let's look inside index.re:

`OCaml
    [%bs.raw {|require('./index.css')|}];

    external register_service_worker : unit => unit = "default" [@@bs.module "./registerServiceWorker"];

    ReactDOMRe.renderToElementWithId <App message="Welcome to React and Reason" /> "root";

    register_service_worker ();

`
There are no `import` or `export` actually, modules are shared by default, using the file name.(If you are familiar with React Native, RN has a `/* provideModule name */` way to make the build tool know it globally, Facebook style~).

But I find that files only under `src/` folder can be accessed, but files under `components/` folder cannot. After some search, that's caused be `bsconfig.json`(aka: BuckleScript Config) file. You must provide exactly what folders you want to use. And just change as following will be fine:

`JSON
    "sources": [{
      "dir": "src",
      "subdirs": [
        "components",
        "containers"
      ]
    }]
`
