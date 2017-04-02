import ReactDOM from 'react-dom';
import { AppContainer } from 'react-hot-loader';
import { Provider } from 'react-redux';
import { createStore } from 'redux';
// import Layout from './src/layout/components/Layout';
import reducers from './reducers';
import Layout from './app/components/Layout';

import { composeWithDevTools } from 'redux-devtools-extension';

const store = createStore(reducers, composeWithDevTools());
const render = Component => ReactDOM.render(
  <AppContainer>
    <Provider store={store}>
       <Component />
    </Provider>
  </AppContainer>,
  document.getElementsByClassName('root')[0],
);

render(Layout);

// Hot module reload
if (module.hot) {
  module.hot.accept('./reducers', () => store.replaceReducer(require('./reducers').default));
  module.hot.accept('./app/components/Layout', () => render(require('./app/components/Layout').default));
}
