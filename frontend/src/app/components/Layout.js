import { Component } from 'react';
import Header from './Header';
import Floors from './Floors';
import Footer from './Footer';
import '../styles/components/layout.scss';

export default class extends Component {
  render() {
    const count = 89;

    return (
      <div className="layout">
        <Header />
        <Floors />
        <Footer count={count} />
      </div>
    );
  }
}
