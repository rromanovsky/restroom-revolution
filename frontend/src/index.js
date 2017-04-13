import ReactDOM from 'react-dom';
import { AppContainer } from 'react-hot-loader';
import { Provider } from 'react-redux';
import { createStore } from 'redux';
import reducer from './redux';
import Layout from './app/components/Layout';
import './app/styles/index.scss';

import { composeWithDevTools } from 'redux-devtools-extension';

const store = createStore(reducer, composeWithDevTools());
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
  module.hot.accept('./redux', () => store.replaceReducer(require('./redux').default));
  module.hot.accept('./app/components/Layout', () => render(require('./app/components/Layout').default));
}
