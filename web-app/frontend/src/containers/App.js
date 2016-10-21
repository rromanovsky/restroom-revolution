import {connect} from 'react-redux';
import App from '../components/App';
import * as actions from '../actions/app.js';
import apiConfig from '../configs/api-config';


const mapStateToProps = ({ app }) => {
  return {
    data: app.data
  };
};

const mapDispatchToProps = (dispatch) => {
  return {
    fetchData: () => {
      setInterval(() => {
        dispatch(actions.fetchData());
      }, apiConfig.API_POOLING_TIME_MS);
    }
  };
};

export default connect(mapStateToProps, mapDispatchToProps)(App);
