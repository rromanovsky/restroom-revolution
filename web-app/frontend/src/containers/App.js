import {connect} from 'react-redux';
import App from '../components/App';
import * as actions from '../actions/app.js';
import apiConfig from '../configs/api-config';


const mapStateToProps = ({ app }) => {
  return { ...app };
};

const mapDispatchToProps = (dispatch) => {
  return {
    fetchData: () => {
      dispatch(actions.fetchData());
    }
  };
};

export default connect(mapStateToProps, mapDispatchToProps)(App);
