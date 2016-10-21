import 'file?name=[name].[ext]!./index.html';
import 'file?name=[name].[ext]!./favicon.ico';
import * as storage from 'redux-storage';
import createEngine from 'redux-storage-engine-sessionstorage';
import thunkMiddleware from 'redux-thunk';
import 'babel-polyfill';

import React from 'react';
import { render } from 'react-dom';
import { Provider } from 'react-redux';

import { createStore, applyMiddleware, compose } from 'redux';
import { Router, Route, IndexRedirect, Redirect, hashHistory } from 'react-router';
import AppContainer from './containers/App';
import reducers from './reducers';

const engine = createEngine('redux-store');
const storageMiddleware = storage.createMiddleware(engine);
const store = createStore(
  storage.reducer(reducers),
  compose(
    applyMiddleware(
      thunkMiddleware,
      storageMiddleware
    ),
    window.devToolsExtension ? window.devToolsExtension() : f => f
  )
);

// const history = syncHistoryWithStore(hashHistory, store);
const load = storage.createLoader(engine);

load(store).then(() => {
  render(
    <Provider store={store}>
      <Router history={hashHistory}>
        <Route path="/" component={AppContainer}>
          <Redirect from="*" to="/"/>
        </Route>
      </Router>
    </Provider>,
    document.getElementById('root')
  );
});
